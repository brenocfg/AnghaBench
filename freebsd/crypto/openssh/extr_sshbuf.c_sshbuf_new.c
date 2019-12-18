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
struct sshbuf {int alloc; int refcount; int /*<<< orphan*/ * d; int /*<<< orphan*/ * cd; int /*<<< orphan*/ * parent; scalar_t__ readonly; int /*<<< orphan*/  max_size; } ;

/* Variables and functions */
 int SSHBUF_SIZE_INIT ; 
 int /*<<< orphan*/  SSHBUF_SIZE_MAX ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct sshbuf*) ; 

struct sshbuf *
sshbuf_new(void)
{
	struct sshbuf *ret;

	if ((ret = calloc(sizeof(*ret), 1)) == NULL)
		return NULL;
	ret->alloc = SSHBUF_SIZE_INIT;
	ret->max_size = SSHBUF_SIZE_MAX;
	ret->readonly = 0;
	ret->refcount = 1;
	ret->parent = NULL;
	if ((ret->cd = ret->d = calloc(1, ret->alloc)) == NULL) {
		free(ret);
		return NULL;
	}
	return ret;
}