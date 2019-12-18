#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
union ng_patch_op_val {int v1; int v2; int v4; int v8; } ;
struct TYPE_8__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
typedef  TYPE_6__* priv_p ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_12__ {int /*<<< orphan*/  patched; } ;
struct TYPE_13__ {TYPE_5__ stats; TYPE_4__* conf; } ;
struct TYPE_11__ {int count; TYPE_3__* ops; } ;
struct TYPE_9__ {int v1; int v2; int v4; int v8; } ;
struct TYPE_10__ {int offset; int length; scalar_t__ mode; TYPE_2__ val; } ;

/* Variables and functions */
#define  NG_PATCH_MODE_ADD 138 
#define  NG_PATCH_MODE_AND 137 
#define  NG_PATCH_MODE_DIV 136 
#define  NG_PATCH_MODE_MUL 135 
#define  NG_PATCH_MODE_NEG 134 
#define  NG_PATCH_MODE_OR 133 
#define  NG_PATCH_MODE_SET 132 
#define  NG_PATCH_MODE_SHL 131 
#define  NG_PATCH_MODE_SHR 130 
#define  NG_PATCH_MODE_SUB 129 
#define  NG_PATCH_MODE_XOR 128 
 int be64toh (int) ; 
 int htobe64 (int) ; 
 int htonl (int) ; 
 int htons (int) ; 
 int /*<<< orphan*/  m_copyback (struct mbuf*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int,int,int /*<<< orphan*/ ) ; 
 int ntohl (int) ; 
 int ntohs (int) ; 

__attribute__((used)) static void
do_patch(priv_p privp, struct mbuf *m, int global_offset)
{
	int i, offset, patched = 0;
	union ng_patch_op_val val;

	for (i = 0; i < privp->conf->count; i++) {
		offset = global_offset + privp->conf->ops[i].offset;

		if (offset + privp->conf->ops[i].length > m->m_pkthdr.len)
			continue;

		/* for "=" operation we don't need to copy data from mbuf */
		if (privp->conf->ops[i].mode != NG_PATCH_MODE_SET)
			m_copydata(m, offset, privp->conf->ops[i].length, (caddr_t) &val);

		switch (privp->conf->ops[i].length)
		{
			case 1:
				switch (privp->conf->ops[i].mode)
				{
					case NG_PATCH_MODE_SET:
						val.v1 = privp->conf->ops[i].val.v1;
						break;
					case NG_PATCH_MODE_ADD:
						val.v1 += privp->conf->ops[i].val.v1;
						break;
					case NG_PATCH_MODE_SUB:
						val.v1 -= privp->conf->ops[i].val.v1;
						break;
					case NG_PATCH_MODE_MUL:
						val.v1 *= privp->conf->ops[i].val.v1;
						break;
					case NG_PATCH_MODE_DIV:
						val.v1 /= privp->conf->ops[i].val.v1;
						break;
					case NG_PATCH_MODE_NEG:
						*((int8_t *) &val) = - *((int8_t *) &val);
						break;
					case NG_PATCH_MODE_AND:
						val.v1 &= privp->conf->ops[i].val.v1;
						break;
					case NG_PATCH_MODE_OR:
						val.v1 |= privp->conf->ops[i].val.v1;
						break;
					case NG_PATCH_MODE_XOR:
						val.v1 ^= privp->conf->ops[i].val.v1;
						break;
					case NG_PATCH_MODE_SHL:
						val.v1 <<= privp->conf->ops[i].val.v1;
						break;
					case NG_PATCH_MODE_SHR:
						val.v1 >>= privp->conf->ops[i].val.v1;
						break;
				}
				break;

			case 2:
				val.v2 = ntohs(val.v2);

				switch (privp->conf->ops[i].mode)
				{
					case NG_PATCH_MODE_SET:
						val.v2 = privp->conf->ops[i].val.v2;
						break;
					case NG_PATCH_MODE_ADD:
						val.v2 += privp->conf->ops[i].val.v2;
						break;
					case NG_PATCH_MODE_SUB:
						val.v2 -= privp->conf->ops[i].val.v2;
						break;
					case NG_PATCH_MODE_MUL:
						val.v2 *= privp->conf->ops[i].val.v2;
						break;
					case NG_PATCH_MODE_DIV:
						val.v2 /= privp->conf->ops[i].val.v2;
						break;
					case NG_PATCH_MODE_NEG:
						*((int16_t *) &val) = - *((int16_t *) &val);
						break;
					case NG_PATCH_MODE_AND:
						val.v2 &= privp->conf->ops[i].val.v2;
						break;
					case NG_PATCH_MODE_OR:
						val.v2 |= privp->conf->ops[i].val.v2;
						break;
					case NG_PATCH_MODE_XOR:
						val.v2 ^= privp->conf->ops[i].val.v2;
						break;
					case NG_PATCH_MODE_SHL:
						val.v2 <<= privp->conf->ops[i].val.v2;
						break;
					case NG_PATCH_MODE_SHR:
						val.v2 >>= privp->conf->ops[i].val.v2;
						break;
				}

				val.v2 = htons(val.v2);

				break;

			case 4:
				val.v4 = ntohl(val.v4);

				switch (privp->conf->ops[i].mode)
				{
					case NG_PATCH_MODE_SET:
						val.v4 = privp->conf->ops[i].val.v4;
						break;
					case NG_PATCH_MODE_ADD:
						val.v4 += privp->conf->ops[i].val.v4;
						break;
					case NG_PATCH_MODE_SUB:
						val.v4 -= privp->conf->ops[i].val.v4;
						break;
					case NG_PATCH_MODE_MUL:
						val.v4 *= privp->conf->ops[i].val.v4;
						break;
					case NG_PATCH_MODE_DIV:
						val.v4 /= privp->conf->ops[i].val.v4;
						break;
					case NG_PATCH_MODE_NEG:
						*((int32_t *) &val) = - *((int32_t *) &val);
						break;
					case NG_PATCH_MODE_AND:
						val.v4 &= privp->conf->ops[i].val.v4;
						break;
					case NG_PATCH_MODE_OR:
						val.v4 |= privp->conf->ops[i].val.v4;
						break;
					case NG_PATCH_MODE_XOR:
						val.v4 ^= privp->conf->ops[i].val.v4;
						break;
					case NG_PATCH_MODE_SHL:
						val.v4 <<= privp->conf->ops[i].val.v4;
						break;
					case NG_PATCH_MODE_SHR:
						val.v4 >>= privp->conf->ops[i].val.v4;
						break;
				}

				val.v4 = htonl(val.v4);

				break;

			case 8:
				val.v8 = be64toh(val.v8);

				switch (privp->conf->ops[i].mode)
				{
					case NG_PATCH_MODE_SET:
						val.v8 = privp->conf->ops[i].val.v8;
						break;
					case NG_PATCH_MODE_ADD:
						val.v8 += privp->conf->ops[i].val.v8;
						break;
					case NG_PATCH_MODE_SUB:
						val.v8 -= privp->conf->ops[i].val.v8;
						break;
					case NG_PATCH_MODE_MUL:
						val.v8 *= privp->conf->ops[i].val.v8;
						break;
					case NG_PATCH_MODE_DIV:
						val.v8 /= privp->conf->ops[i].val.v8;
						break;
					case NG_PATCH_MODE_NEG:
						*((int64_t *) &val) = - *((int64_t *) &val);
						break;
					case NG_PATCH_MODE_AND:
						val.v8 &= privp->conf->ops[i].val.v8;
						break;
					case NG_PATCH_MODE_OR:
						val.v8 |= privp->conf->ops[i].val.v8;
						break;
					case NG_PATCH_MODE_XOR:
						val.v8 ^= privp->conf->ops[i].val.v8;
						break;
					case NG_PATCH_MODE_SHL:
						val.v8 <<= privp->conf->ops[i].val.v8;
						break;
					case NG_PATCH_MODE_SHR:
						val.v8 >>= privp->conf->ops[i].val.v8;
						break;
				}

				val.v8 = htobe64(val.v8);

				break;
		}

		m_copyback(m, offset, privp->conf->ops[i].length, (caddr_t) &val);
		patched = 1;
	}

	if (patched)
		privp->stats.patched++;
}