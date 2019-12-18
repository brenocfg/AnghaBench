#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {void* op; void* keylen; void* algo; } ;
struct TYPE_17__ {TYPE_2__ para; } ;
struct TYPE_18__ {TYPE_3__ cipher; } ;
struct TYPE_19__ {TYPE_4__ u; void* op_type; } ;
struct TYPE_20__ {TYPE_5__ sym_create_session; } ;
struct TYPE_15__ {void* algo; scalar_t__ queue_id; void* opcode; } ;
struct TYPE_23__ {int /*<<< orphan*/  session_id; void* status; TYPE_6__ u; TYPE_1__ header; } ;
typedef  TYPE_9__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_22__ {void* session_id; } ;
struct TYPE_21__ {void* session_id; } ;
struct virtio_crypto_ablkcipher_ctx {TYPE_8__ dec_sess_info; TYPE_7__ enc_sess_info; struct virtio_crypto* vcrypto; } ;
struct virtio_crypto {int /*<<< orphan*/  ctrl_lock; TYPE_9__ input; int /*<<< orphan*/  ctrl_vq; TYPE_9__ ctrl; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int VIRTIO_CRYPTO_CIPHER_CREATE_SESSION ; 
 int VIRTIO_CRYPTO_ERR ; 
 scalar_t__ VIRTIO_CRYPTO_OK ; 
 int VIRTIO_CRYPTO_OP_DECRYPT ; 
 int VIRTIO_CRYPTO_OP_ENCRYPT ; 
 int VIRTIO_CRYPTO_SYM_OP_CIPHER ; 
 int /*<<< orphan*/  cpu_relax () ; 
 void* cpu_to_le32 (int) ; 
 TYPE_9__* kmemdup (TYPE_9__ const*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (TYPE_9__*) ; 
 scalar_t__ le32_to_cpu (void*) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,TYPE_9__*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int virtqueue_add_sgs (int /*<<< orphan*/ ,struct scatterlist**,unsigned int,unsigned int,struct virtio_crypto*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_get_buf (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  virtqueue_is_broken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_kick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtio_crypto_alg_ablkcipher_init_session(
		struct virtio_crypto_ablkcipher_ctx *ctx,
		uint32_t alg, const uint8_t *key,
		unsigned int keylen,
		int encrypt)
{
	struct scatterlist outhdr, key_sg, inhdr, *sgs[3];
	unsigned int tmp;
	struct virtio_crypto *vcrypto = ctx->vcrypto;
	int op = encrypt ? VIRTIO_CRYPTO_OP_ENCRYPT : VIRTIO_CRYPTO_OP_DECRYPT;
	int err;
	unsigned int num_out = 0, num_in = 0;

	/*
	 * Avoid to do DMA from the stack, switch to using
	 * dynamically-allocated for the key
	 */
	uint8_t *cipher_key = kmemdup(key, keylen, GFP_ATOMIC);

	if (!cipher_key)
		return -ENOMEM;

	spin_lock(&vcrypto->ctrl_lock);
	/* Pad ctrl header */
	vcrypto->ctrl.header.opcode =
		cpu_to_le32(VIRTIO_CRYPTO_CIPHER_CREATE_SESSION);
	vcrypto->ctrl.header.algo = cpu_to_le32(alg);
	/* Set the default dataqueue id to 0 */
	vcrypto->ctrl.header.queue_id = 0;

	vcrypto->input.status = cpu_to_le32(VIRTIO_CRYPTO_ERR);
	/* Pad cipher's parameters */
	vcrypto->ctrl.u.sym_create_session.op_type =
		cpu_to_le32(VIRTIO_CRYPTO_SYM_OP_CIPHER);
	vcrypto->ctrl.u.sym_create_session.u.cipher.para.algo =
		vcrypto->ctrl.header.algo;
	vcrypto->ctrl.u.sym_create_session.u.cipher.para.keylen =
		cpu_to_le32(keylen);
	vcrypto->ctrl.u.sym_create_session.u.cipher.para.op =
		cpu_to_le32(op);

	sg_init_one(&outhdr, &vcrypto->ctrl, sizeof(vcrypto->ctrl));
	sgs[num_out++] = &outhdr;

	/* Set key */
	sg_init_one(&key_sg, cipher_key, keylen);
	sgs[num_out++] = &key_sg;

	/* Return status and session id back */
	sg_init_one(&inhdr, &vcrypto->input, sizeof(vcrypto->input));
	sgs[num_out + num_in++] = &inhdr;

	err = virtqueue_add_sgs(vcrypto->ctrl_vq, sgs, num_out,
				num_in, vcrypto, GFP_ATOMIC);
	if (err < 0) {
		spin_unlock(&vcrypto->ctrl_lock);
		kzfree(cipher_key);
		return err;
	}
	virtqueue_kick(vcrypto->ctrl_vq);

	/*
	 * Trapping into the hypervisor, so the request should be
	 * handled immediately.
	 */
	while (!virtqueue_get_buf(vcrypto->ctrl_vq, &tmp) &&
	       !virtqueue_is_broken(vcrypto->ctrl_vq))
		cpu_relax();

	if (le32_to_cpu(vcrypto->input.status) != VIRTIO_CRYPTO_OK) {
		spin_unlock(&vcrypto->ctrl_lock);
		pr_err("virtio_crypto: Create session failed status: %u\n",
			le32_to_cpu(vcrypto->input.status));
		kzfree(cipher_key);
		return -EINVAL;
	}

	if (encrypt)
		ctx->enc_sess_info.session_id =
			le64_to_cpu(vcrypto->input.session_id);
	else
		ctx->dec_sess_info.session_id =
			le64_to_cpu(vcrypto->input.session_id);

	spin_unlock(&vcrypto->ctrl_lock);

	kzfree(cipher_key);
	return 0;
}