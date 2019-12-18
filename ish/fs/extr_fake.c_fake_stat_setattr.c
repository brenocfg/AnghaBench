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
struct ish_stat {int mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct attr {int type; int mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int S_IFMT ; 
#define  attr_gid 130 
#define  attr_mode 129 
#define  attr_uid 128 

__attribute__((used)) static void fake_stat_setattr(struct ish_stat *ishstat, struct attr attr) {
    switch (attr.type) {
        case attr_uid:
            ishstat->uid = attr.uid;
            break;
        case attr_gid:
            ishstat->gid = attr.gid;
            break;
        case attr_mode:
            ishstat->mode = (ishstat->mode & S_IFMT) | (attr.mode & ~S_IFMT);
            break;
    }
}