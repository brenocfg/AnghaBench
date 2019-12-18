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
struct fd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_CHAR ; 
 int dyn_open (int /*<<< orphan*/ ,int,int,struct fd*) ; 

__attribute__((used)) static int dyn_open_char(int major, int minor, struct fd *fd) {
    return dyn_open(DEV_CHAR, major, minor, fd);
}