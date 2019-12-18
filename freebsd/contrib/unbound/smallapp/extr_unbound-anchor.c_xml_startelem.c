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
struct xml_data {int /*<<< orphan*/  tag; int /*<<< orphan*/  use_key; int /*<<< orphan*/ * czone; } ;
typedef  char XML_Char ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_keydigest (struct xml_data*,char const**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int verb ; 
 int /*<<< orphan*/ * xml_selectbio (struct xml_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xml_startelem(void *userData, const XML_Char *name, const XML_Char **atts)
{
	struct xml_data* data = (struct xml_data*)userData;
	BIO* b;
	if(verb>=4) printf("xml tag start '%s'\n", name);
	free(data->tag);
	data->tag = strdup(name);
	if(!data->tag) {
		if(verb) printf("out of memory\n");
		exit(0);
	}
	if(verb>=4) {
		int i;
		for(i=0; atts[i]; i+=2) {
			printf("  %s='%s'\n", atts[i], atts[i+1]);
		}
	}
	/* handle attributes to particular types */
	if(strcasecmp(name, "KeyDigest") == 0) {
		handle_keydigest(data, atts);
		return;
	} else if(strcasecmp(name, "Zone") == 0) {
		(void)BIO_reset(data->czone);
		return;
	}

	/* for other types we prepare to pick up the data */
	if(!data->use_key)
		return;
	b = xml_selectbio(data, data->tag);
	if(b) {
		/* empty it */
		(void)BIO_reset(b);
	}
}