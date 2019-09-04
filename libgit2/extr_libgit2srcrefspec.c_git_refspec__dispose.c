#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  string; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
typedef  TYPE_1__ git_refspec ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 

void git_refspec__dispose(git_refspec *refspec)
{
	if (refspec == NULL)
		return;

	git__free(refspec->src);
	git__free(refspec->dst);
	git__free(refspec->string);

	memset(refspec, 0x0, sizeof(git_refspec));
}