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
typedef  int /*<<< orphan*/  uint8_t ;
struct config_file {scalar_t__ num_tags; } ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,size_t) ; 
 int /*<<< orphan*/  cfg_set_bit (int /*<<< orphan*/ *,size_t,int) ; 
 int find_tag_id (struct config_file*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 char* strsep (char**,char*) ; 

uint8_t* config_parse_taglist(struct config_file* cfg, char* str,
        size_t* listlen)
{
	uint8_t* taglist = NULL;
	size_t len = 0;
	char* p, *s;

	/* allocate */
	if(cfg->num_tags == 0) {
		log_err("parse taglist, but no tags defined");
		return 0;
	}
	len = (size_t)(cfg->num_tags+7)/8;
	taglist = calloc(1, len);
	if(!taglist) {
		log_err("out of memory");
		return 0;
	}
	
	/* parse */
	s = str;
	while((p=strsep(&s, " \t\n")) != NULL) {
		if(*p) {
			int id = find_tag_id(cfg, p);
			/* set this bit in the bitlist */
			if(id == -1) {
				log_err("unknown tag: %s", p);
				free(taglist);
				return 0;
			}
			cfg_set_bit(taglist, len, id);
		}
	}

	*listlen = len;
	return taglist;
}