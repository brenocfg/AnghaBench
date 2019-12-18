#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int const u64 ;
typedef  scalar_t__ u32 ;
struct flat_binder_object {int /*<<< orphan*/  handle; scalar_t__ binder; } ;
struct binder_ref_data {int const desc; int /*<<< orphan*/  debug_id; } ;
struct binder_proc {int /*<<< orphan*/  alloc; int /*<<< orphan*/  tsk; int /*<<< orphan*/  pid; } ;
struct binder_object_header {int type; } ;
struct binder_object {struct binder_object_header hdr; } ;
struct binder_node {scalar_t__ ptr; int /*<<< orphan*/  debug_id; } ;
struct binder_fd_array_object {int num_fds; scalar_t__ parent_offset; int /*<<< orphan*/  parent; } ;
struct binder_buffer_object {scalar_t__ length; int /*<<< orphan*/  buffer; } ;
struct binder_buffer {int debug_id; scalar_t__ offsets_size; int /*<<< orphan*/  user_data; int /*<<< orphan*/  data_size; struct binder_node* target_node; } ;
typedef  int /*<<< orphan*/  object_offset ;
typedef  int /*<<< orphan*/  fd ;
typedef  scalar_t__ binder_size_t ;
struct TYPE_2__ {int /*<<< orphan*/  group_leader; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BINDER_DEBUG_TRANSACTION ; 
#define  BINDER_TYPE_BINDER 134 
#define  BINDER_TYPE_FD 133 
#define  BINDER_TYPE_FDA 132 
#define  BINDER_TYPE_HANDLE 131 
#define  BINDER_TYPE_PTR 130 
#define  BINDER_TYPE_WEAK_BINDER 129 
#define  BINDER_TYPE_WEAK_HANDLE 128 
 int SIZE_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int binder_alloc_copy_from_buffer (int /*<<< orphan*/ *,scalar_t__*,struct binder_buffer*,scalar_t__,int) ; 
 int /*<<< orphan*/  binder_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int const,...) ; 
 int /*<<< orphan*/  binder_dec_node (struct binder_node*,int,int /*<<< orphan*/ ) ; 
 int binder_dec_ref_for_handle (struct binder_proc*,int /*<<< orphan*/ ,int,struct binder_ref_data*) ; 
 int /*<<< orphan*/  binder_deferred_fd_close (scalar_t__) ; 
 struct binder_node* binder_get_node (struct binder_proc*,scalar_t__) ; 
 size_t binder_get_object (struct binder_proc*,struct binder_buffer*,scalar_t__,struct binder_object*) ; 
 int /*<<< orphan*/  binder_put_node (struct binder_node*) ; 
 struct binder_buffer_object* binder_validate_ptr (struct binder_proc*,struct binder_buffer*,struct binder_object*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 struct binder_fd_array_object* to_binder_fd_array_object (struct binder_object_header*) ; 
 struct flat_binder_object* to_flat_binder_object (struct binder_object_header*) ; 

__attribute__((used)) static void binder_transaction_buffer_release(struct binder_proc *proc,
					      struct binder_buffer *buffer,
					      binder_size_t failed_at,
					      bool is_failure)
{
	int debug_id = buffer->debug_id;
	binder_size_t off_start_offset, buffer_offset, off_end_offset;

	binder_debug(BINDER_DEBUG_TRANSACTION,
		     "%d buffer release %d, size %zd-%zd, failed at %llx\n",
		     proc->pid, buffer->debug_id,
		     buffer->data_size, buffer->offsets_size,
		     (unsigned long long)failed_at);

	if (buffer->target_node)
		binder_dec_node(buffer->target_node, 1, 0);

	off_start_offset = ALIGN(buffer->data_size, sizeof(void *));
	off_end_offset = is_failure ? failed_at :
				off_start_offset + buffer->offsets_size;
	for (buffer_offset = off_start_offset; buffer_offset < off_end_offset;
	     buffer_offset += sizeof(binder_size_t)) {
		struct binder_object_header *hdr;
		size_t object_size = 0;
		struct binder_object object;
		binder_size_t object_offset;

		if (!binder_alloc_copy_from_buffer(&proc->alloc, &object_offset,
						   buffer, buffer_offset,
						   sizeof(object_offset)))
			object_size = binder_get_object(proc, buffer,
							object_offset, &object);
		if (object_size == 0) {
			pr_err("transaction release %d bad object at offset %lld, size %zd\n",
			       debug_id, (u64)object_offset, buffer->data_size);
			continue;
		}
		hdr = &object.hdr;
		switch (hdr->type) {
		case BINDER_TYPE_BINDER:
		case BINDER_TYPE_WEAK_BINDER: {
			struct flat_binder_object *fp;
			struct binder_node *node;

			fp = to_flat_binder_object(hdr);
			node = binder_get_node(proc, fp->binder);
			if (node == NULL) {
				pr_err("transaction release %d bad node %016llx\n",
				       debug_id, (u64)fp->binder);
				break;
			}
			binder_debug(BINDER_DEBUG_TRANSACTION,
				     "        node %d u%016llx\n",
				     node->debug_id, (u64)node->ptr);
			binder_dec_node(node, hdr->type == BINDER_TYPE_BINDER,
					0);
			binder_put_node(node);
		} break;
		case BINDER_TYPE_HANDLE:
		case BINDER_TYPE_WEAK_HANDLE: {
			struct flat_binder_object *fp;
			struct binder_ref_data rdata;
			int ret;

			fp = to_flat_binder_object(hdr);
			ret = binder_dec_ref_for_handle(proc, fp->handle,
				hdr->type == BINDER_TYPE_HANDLE, &rdata);

			if (ret) {
				pr_err("transaction release %d bad handle %d, ret = %d\n",
				 debug_id, fp->handle, ret);
				break;
			}
			binder_debug(BINDER_DEBUG_TRANSACTION,
				     "        ref %d desc %d\n",
				     rdata.debug_id, rdata.desc);
		} break;

		case BINDER_TYPE_FD: {
			/*
			 * No need to close the file here since user-space
			 * closes it for for successfully delivered
			 * transactions. For transactions that weren't
			 * delivered, the new fd was never allocated so
			 * there is no need to close and the fput on the
			 * file is done when the transaction is torn
			 * down.
			 */
			WARN_ON(failed_at &&
				proc->tsk == current->group_leader);
		} break;
		case BINDER_TYPE_PTR:
			/*
			 * Nothing to do here, this will get cleaned up when the
			 * transaction buffer gets freed
			 */
			break;
		case BINDER_TYPE_FDA: {
			struct binder_fd_array_object *fda;
			struct binder_buffer_object *parent;
			struct binder_object ptr_object;
			binder_size_t fda_offset;
			size_t fd_index;
			binder_size_t fd_buf_size;
			binder_size_t num_valid;

			if (proc->tsk != current->group_leader) {
				/*
				 * Nothing to do if running in sender context
				 * The fd fixups have not been applied so no
				 * fds need to be closed.
				 */
				continue;
			}

			num_valid = (buffer_offset - off_start_offset) /
						sizeof(binder_size_t);
			fda = to_binder_fd_array_object(hdr);
			parent = binder_validate_ptr(proc, buffer, &ptr_object,
						     fda->parent,
						     off_start_offset,
						     NULL,
						     num_valid);
			if (!parent) {
				pr_err("transaction release %d bad parent offset\n",
				       debug_id);
				continue;
			}
			fd_buf_size = sizeof(u32) * fda->num_fds;
			if (fda->num_fds >= SIZE_MAX / sizeof(u32)) {
				pr_err("transaction release %d invalid number of fds (%lld)\n",
				       debug_id, (u64)fda->num_fds);
				continue;
			}
			if (fd_buf_size > parent->length ||
			    fda->parent_offset > parent->length - fd_buf_size) {
				/* No space for all file descriptors here. */
				pr_err("transaction release %d not enough space for %lld fds in buffer\n",
				       debug_id, (u64)fda->num_fds);
				continue;
			}
			/*
			 * the source data for binder_buffer_object is visible
			 * to user-space and the @buffer element is the user
			 * pointer to the buffer_object containing the fd_array.
			 * Convert the address to an offset relative to
			 * the base of the transaction buffer.
			 */
			fda_offset =
			    (parent->buffer - (uintptr_t)buffer->user_data) +
			    fda->parent_offset;
			for (fd_index = 0; fd_index < fda->num_fds;
			     fd_index++) {
				u32 fd;
				int err;
				binder_size_t offset = fda_offset +
					fd_index * sizeof(fd);

				err = binder_alloc_copy_from_buffer(
						&proc->alloc, &fd, buffer,
						offset, sizeof(fd));
				WARN_ON(err);
				if (!err)
					binder_deferred_fd_close(fd);
			}
		} break;
		default:
			pr_err("transaction release %d bad object type %x\n",
				debug_id, hdr->type);
			break;
		}
	}
}