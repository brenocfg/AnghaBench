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
struct xml_data {int /*<<< orphan*/  czone; scalar_t__ use_key; int /*<<< orphan*/ * tag; } ;
typedef  char XML_Char ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int verb ; 
 int /*<<< orphan*/  xml_append_ds (struct xml_data*) ; 
 int /*<<< orphan*/  xml_is_zone_name (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
xml_endelem(void *userData, const XML_Char *name)
{
	struct xml_data* data = (struct xml_data*)userData;
	if(verb>=4) printf("xml tag end   '%s'\n", name);
	free(data->tag);
	data->tag = NULL;
	if(strcasecmp(name, "KeyDigest") == 0) {
		if(data->use_key)
			xml_append_ds(data);
		data->use_key = 0;
	} else if(strcasecmp(name, "Zone") == 0) {
		if(!xml_is_zone_name(data->czone, ".")) {
			if(verb) printf("xml not for the right zone\n");
			exit(0);
		}
	}
}