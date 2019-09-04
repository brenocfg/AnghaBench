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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void sendfile_setup(int f) {
  ASSERT(6 == write(f, "begin\n", 6));
  ASSERT(65542 == lseek(f, 65536, SEEK_CUR));
  ASSERT(4 == write(f, "end\n", 4));
}