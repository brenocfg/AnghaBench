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
struct sbuf {int dummy; } ;
struct cam_path {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,char*,size_t,int /*<<< orphan*/ ) ; 
 int xpt_path_sbuf (struct cam_path*,struct sbuf*) ; 

int
xpt_path_string(struct cam_path *path, char *str, size_t str_len)
{
	struct sbuf sb;
	int len;

	sbuf_new(&sb, str, str_len, 0);
	len = xpt_path_sbuf(path, &sb);
	sbuf_finish(&sb);
	return (len);
}