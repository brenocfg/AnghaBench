#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct per_user_data {int /*<<< orphan*/  user_data_lock; int /*<<< orphan*/  file_offset; } ;
struct file_offset_struct {scalar_t__ file_offset; int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GNTDEV ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct file_offset_struct*) ; 
 struct file_offset_struct* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct file_offset_struct*) ; 
 struct file_offset_struct* RB_PREV (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct file_offset_struct*) ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct file_offset_struct*) ; 
 int /*<<< orphan*/  file_offset_head ; 
 int /*<<< orphan*/  free (struct file_offset_struct*,int /*<<< orphan*/ ) ; 
 struct file_offset_struct* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
put_file_offset(struct per_user_data *priv_user, uint32_t count,
    uint64_t file_offset)
{
	struct file_offset_struct *offset, *offset_nxt, *offset_prv;

	offset = malloc(sizeof(*offset), M_GNTDEV, M_WAITOK | M_ZERO);
	offset->file_offset = file_offset;
	offset->count = count;

	mtx_lock(&priv_user->user_data_lock);
	RB_INSERT(file_offset_head, &priv_user->file_offset, offset);
	offset_nxt = RB_NEXT(file_offset_head, &priv_user->file_offset, offset);
	offset_prv = RB_PREV(file_offset_head, &priv_user->file_offset, offset);
	if (offset_nxt != NULL &&
	    offset_nxt->file_offset == offset->file_offset + offset->count *
	    PAGE_SIZE) {
		offset->count += offset_nxt->count;
		RB_REMOVE(file_offset_head, &priv_user->file_offset,
		    offset_nxt);
		free(offset_nxt, M_GNTDEV);
	}
	if (offset_prv != NULL &&
	    offset->file_offset == offset_prv->file_offset + offset_prv->count *
	    PAGE_SIZE) {
		offset_prv->count += offset->count;
		RB_REMOVE(file_offset_head, &priv_user->file_offset, offset);
		free(offset, M_GNTDEV);
	}
	mtx_unlock(&priv_user->user_data_lock);
}