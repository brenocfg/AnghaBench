#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int off_t ;
struct TYPE_8__ {int attr; int /*<<< orphan*/  clus; int /*<<< orphan*/  size; } ;
struct TYPE_7__ {int dirents; } ;
typedef  TYPE_1__ DOS_FS ;
typedef  TYPE_2__ DOS_DE ;

/* Variables and functions */
 int FA_DIR ; 
 int blkbyt (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cv2 (int /*<<< orphan*/ ) ; 
 int cv4 (int /*<<< orphan*/ ) ; 
 int fatcnt (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static off_t
fsize(DOS_FS *fs, DOS_DE *de)
{
   u_long size;
   u_int c;
   int n;

   if (!(size = cv4(de->size)) && de->attr & FA_DIR) {
      if (!(c = cv2(de->clus)))
         size = fs->dirents * sizeof(DOS_DE);
      else {
         if ((n = fatcnt(fs, c)) == -1)
            return (n);
         size = blkbyt(fs, n);
      }
   }
   return (size);
}