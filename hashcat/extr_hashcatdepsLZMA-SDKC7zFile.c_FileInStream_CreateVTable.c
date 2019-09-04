#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Seek; int /*<<< orphan*/  Read; } ;
struct TYPE_5__ {TYPE_1__ vt; } ;
typedef  TYPE_2__ CFileInStream ;

/* Variables and functions */
 int /*<<< orphan*/  FileInStream_Read ; 
 int /*<<< orphan*/  FileInStream_Seek ; 

void FileInStream_CreateVTable(CFileInStream *p)
{
  p->vt.Read = FileInStream_Read;
  p->vt.Seek = FileInStream_Seek;
}