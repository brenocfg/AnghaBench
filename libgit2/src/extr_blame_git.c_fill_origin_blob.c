#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* ptr; size_t size; } ;
typedef  TYPE_1__ mmfile_t ;
struct TYPE_7__ {scalar_t__ blob; } ;
typedef  TYPE_2__ git_blame__origin ;

/* Variables and functions */
 scalar_t__ git_blob_rawcontent (scalar_t__) ; 
 scalar_t__ git_blob_rawsize (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fill_origin_blob(git_blame__origin *o, mmfile_t *file)
{
	memset(file, 0, sizeof(*file));
	if (o->blob) {
		file->ptr = (char*)git_blob_rawcontent(o->blob);
		file->size = (size_t)git_blob_rawsize(o->blob);
	}
}