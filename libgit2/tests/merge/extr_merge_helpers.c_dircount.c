#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int git_buf_len (TYPE_1__*) ; 
 scalar_t__ strcmp (int,char*) ; 

int dircount(void *payload, git_buf *pathbuf)
{
	size_t *entries = payload;
	size_t len = git_buf_len(pathbuf);

	if (len < 5 || strcmp(pathbuf->ptr + (git_buf_len(pathbuf) - 5), "/.git") != 0)
		(*entries)++;

	return 0;
}