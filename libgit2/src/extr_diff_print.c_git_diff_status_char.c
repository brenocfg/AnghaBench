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
typedef  int git_delta_t ;

/* Variables and functions */
#define  GIT_DELTA_ADDED 136 
#define  GIT_DELTA_COPIED 135 
#define  GIT_DELTA_DELETED 134 
#define  GIT_DELTA_IGNORED 133 
#define  GIT_DELTA_MODIFIED 132 
#define  GIT_DELTA_RENAMED 131 
#define  GIT_DELTA_TYPECHANGE 130 
#define  GIT_DELTA_UNREADABLE 129 
#define  GIT_DELTA_UNTRACKED 128 

char git_diff_status_char(git_delta_t status)
{
	char code;

	switch (status) {
	case GIT_DELTA_ADDED:      code = 'A'; break;
	case GIT_DELTA_DELETED:    code = 'D'; break;
	case GIT_DELTA_MODIFIED:   code = 'M'; break;
	case GIT_DELTA_RENAMED:    code = 'R'; break;
	case GIT_DELTA_COPIED:     code = 'C'; break;
	case GIT_DELTA_IGNORED:    code = 'I'; break;
	case GIT_DELTA_UNTRACKED:  code = '?'; break;
	case GIT_DELTA_TYPECHANGE: code = 'T'; break;
	case GIT_DELTA_UNREADABLE: code = 'X'; break;
	default:                   code = ' '; break;
	}

	return code;
}