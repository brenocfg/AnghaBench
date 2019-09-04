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
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void tar_fill_ustar_magic (char b[512]) {
  strcpy (b + 257, "ustar");
  memcpy (b + 263, "00", 2);
}