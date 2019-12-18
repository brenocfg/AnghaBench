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
typedef  int /*<<< orphan*/  ufs_ino_t ;

/* Variables and functions */
 scalar_t__ fsread (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
xfsread(ufs_ino_t inode, void *buf, size_t nbyte)
{

	if ((size_t)fsread(inode, buf, nbyte) != nbyte) {
		printf("Invalid %s\n", "format");
		return (-1);
	}
	return (0);
}