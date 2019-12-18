#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ count; int /*<<< orphan*/  out_port; } ;
typedef  TYPE_1__ osm_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 int fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ ftruncate (int,int /*<<< orphan*/ ) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void truncate_log_file(osm_log_t * p_log)
{
	int fd = fileno(p_log->out_port);
	if (ftruncate(fd, 0) < 0)
		fprintf(stderr, "truncate_log_file: cannot truncate: %s\n",
			strerror(errno));
	if (lseek(fd, 0, SEEK_SET) < 0)
		fprintf(stderr, "truncate_log_file: cannot rewind: %s\n",
			strerror(errno));
	p_log->count = 0;
}