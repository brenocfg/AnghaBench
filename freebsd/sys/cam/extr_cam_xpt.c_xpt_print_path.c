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
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 int XPT_PRINT_LEN ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_path_sbuf (struct cam_path*,struct sbuf*) ; 

void
xpt_print_path(struct cam_path *path)
{
	struct sbuf sb;
	char buffer[XPT_PRINT_LEN];

	sbuf_new(&sb, buffer, XPT_PRINT_LEN, SBUF_FIXEDLEN);
	xpt_path_sbuf(path, &sb);
	sbuf_finish(&sb);
	printf("%s", sbuf_data(&sb));
	sbuf_delete(&sb);
}