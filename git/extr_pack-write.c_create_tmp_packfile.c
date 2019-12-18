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
struct strbuf {int dummy; } ;
struct hashfile {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 struct hashfile* hashfd (int,char*) ; 
 int odb_mkstemp (struct strbuf*,char*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 

struct hashfile *create_tmp_packfile(char **pack_tmp_name)
{
	struct strbuf tmpname = STRBUF_INIT;
	int fd;

	fd = odb_mkstemp(&tmpname, "pack/tmp_pack_XXXXXX");
	*pack_tmp_name = strbuf_detach(&tmpname, NULL);
	return hashfd(fd, *pack_tmp_name);
}