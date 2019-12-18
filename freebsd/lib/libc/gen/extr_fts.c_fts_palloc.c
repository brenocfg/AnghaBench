#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t fts_pathlen; int /*<<< orphan*/ * fts_path; } ;
typedef  TYPE_1__ FTS ;

/* Variables and functions */
 int /*<<< orphan*/ * reallocf (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
fts_palloc(FTS *sp, size_t more)
{

	sp->fts_pathlen += more + 256;
	sp->fts_path = reallocf(sp->fts_path, sp->fts_pathlen);
	return (sp->fts_path == NULL);
}