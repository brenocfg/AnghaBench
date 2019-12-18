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
struct revoked_blob {size_t len; struct revoked_blob* blob; } ;
typedef  struct revoked_blob u_char ;
struct revoked_blob_tree {int dummy; } ;

/* Variables and functions */
 struct revoked_blob* RB_INSERT (int /*<<< orphan*/ ,struct revoked_blob_tree*,struct revoked_blob*) ; 
 int SSH_ERR_ALLOC_FAIL ; 
 struct revoked_blob* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct revoked_blob*) ; 
 int /*<<< orphan*/  revoked_blob_tree ; 

__attribute__((used)) static int
revoke_blob(struct revoked_blob_tree *rbt, u_char *blob, size_t len)
{
	struct revoked_blob *rb, *erb;

	if ((rb = calloc(1, sizeof(*rb))) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	rb->blob = blob;
	rb->len = len;
	erb = RB_INSERT(revoked_blob_tree, rbt, rb);
	if (erb != NULL) {
		free(rb->blob);
		free(rb);
	}
	return 0;
}