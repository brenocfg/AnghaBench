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
typedef  union ctl_io {int dummy; } ctl_io ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 int /*<<< orphan*/  ctl_io_sbuf (union ctl_io*,struct sbuf*) ; 
 char* sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,char*,int,int /*<<< orphan*/ ) ; 

char *
ctl_io_string(union ctl_io *io, char *str, int str_len)
{
	struct sbuf sb;

	sbuf_new(&sb, str, str_len, SBUF_FIXEDLEN);
	ctl_io_sbuf(io, &sb);
	sbuf_finish(&sb);
	return (sbuf_data(&sb));
}