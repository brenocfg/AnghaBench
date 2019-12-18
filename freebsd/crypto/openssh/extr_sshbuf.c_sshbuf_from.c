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
struct sshbuf {size_t alloc; size_t size; size_t max_size; int readonly; int refcount; int /*<<< orphan*/ * d; void const* cd; int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 size_t SSHBUF_SIZE_MAX ; 
 struct sshbuf* calloc (int,int) ; 

struct sshbuf *
sshbuf_from(const void *blob, size_t len)
{
	struct sshbuf *ret;

	if (blob == NULL || len > SSHBUF_SIZE_MAX ||
	    (ret = calloc(sizeof(*ret), 1)) == NULL)
		return NULL;
	ret->alloc = ret->size = ret->max_size = len;
	ret->readonly = 1;
	ret->refcount = 1;
	ret->parent = NULL;
	ret->cd = blob;
	ret->d = NULL;
	return ret;
}