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
struct xml_data {char* tag; scalar_t__ use_key; int /*<<< orphan*/ * czone; } ;
typedef  int XML_Char ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ BIO_write (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int verb ; 
 int /*<<< orphan*/ * xml_selectbio (struct xml_data*,char*) ; 

__attribute__((used)) static void
xml_charhandle(void *userData, const XML_Char *s, int len)
{
	struct xml_data* data = (struct xml_data*)userData;
	BIO* b = NULL;
	/* skip characters outside of elements */
	if(!data->tag)
		return;
	if(verb>=4) {
		int i;
		printf("%s%s charhandle: '",
			data->use_key?"use ":"",
			data->tag?data->tag:"none");
		for(i=0; i<len; i++)
			printf("%c", s[i]);
		printf("'\n");
	}
	if(strcasecmp(data->tag, "Zone") == 0) {
		if(BIO_write(data->czone, s, len) < 0) {
			if(verb) printf("out of memory in BIO_write\n");
			exit(0);
		}
		return;
	}
	/* only store if key is used */
	if(!data->use_key)
		return;
	b = xml_selectbio(data, data->tag);
	if(b) {
		if(BIO_write(b, s, len) < 0) {
			if(verb) printf("out of memory in BIO_write\n");
			exit(0);
		}
	}
}