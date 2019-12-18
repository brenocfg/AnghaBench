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
struct config_file {int num_tags; char** tagname; } ;

/* Variables and functions */
 int find_tag_id (struct config_file*,char const*) ; 
 int /*<<< orphan*/  free (char**) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char**,char**,int) ; 
 char* strdup (char const*) ; 

int
config_add_tag(struct config_file* cfg, const char* tag)
{
	char** newarray;
	char* newtag;
	if(find_tag_id(cfg, tag) != -1)
		return 1; /* nothing to do */
	newarray = (char**)malloc(sizeof(char*)*(cfg->num_tags+1));
	if(!newarray)
		return 0;
	newtag = strdup(tag);
	if(!newtag) {
		free(newarray);
		return 0;
	}
	if(cfg->tagname) {
		memcpy(newarray, cfg->tagname, sizeof(char*)*cfg->num_tags);
		free(cfg->tagname);
	}
	newarray[cfg->num_tags++] = newtag;
	cfg->tagname = newarray;
	return 1;
}