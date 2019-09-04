#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* pack; } ;
typedef  TYPE_2__ git_indexer ;
struct TYPE_7__ {int /*<<< orphan*/  size; } ;
struct TYPE_5__ {TYPE_4__ mwf; } ;

/* Variables and functions */
 scalar_t__ GIT_OID_RAWSZ ; 
 int /*<<< orphan*/  git_mwindow_free_all (TYPE_4__*) ; 

__attribute__((used)) static void seek_back_trailer(git_indexer *idx)
{
	idx->pack->mwf.size -= GIT_OID_RAWSZ;
	git_mwindow_free_all(&idx->pack->mwf);
}