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
struct roff {int options; int format; int mstackpos; int rstackpos; char escape; int /*<<< orphan*/  reqtab; } ;

/* Variables and functions */
 int MPARSE_MAN ; 
 int MPARSE_MDOC ; 
 int /*<<< orphan*/  ROFF_RENAMED ; 
 struct roff* mandoc_calloc (int,int) ; 
 int /*<<< orphan*/  roffhash_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct roff *
roff_alloc(int options)
{
	struct roff	*r;

	r = mandoc_calloc(1, sizeof(struct roff));
	r->reqtab = roffhash_alloc(0, ROFF_RENAMED);
	r->options = options;
	r->format = options & (MPARSE_MDOC | MPARSE_MAN);
	r->mstackpos = -1;
	r->rstackpos = -1;
	r->escape = '\\';
	return r;
}