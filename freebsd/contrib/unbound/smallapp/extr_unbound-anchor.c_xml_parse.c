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
typedef  int /*<<< orphan*/  time_t ;
struct xml_data {int num_keys; int /*<<< orphan*/ * ds; int /*<<< orphan*/ * cdigest; int /*<<< orphan*/ * cdigtype; int /*<<< orphan*/ * calgo; int /*<<< orphan*/ * ctag; int /*<<< orphan*/ * czone; int /*<<< orphan*/  tag; } ;
typedef  int /*<<< orphan*/  XML_Parser ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int BIO_get_mem_data (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  BIO_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* XML_ErrorString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_GetErrorCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_Parse (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  XML_ParserCreate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XML_ParserFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int verb ; 
 int /*<<< orphan*/  xml_parse_setup (int /*<<< orphan*/ ,struct xml_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BIO*
xml_parse(BIO* xml, time_t now)
{
	char* pp;
	int len;
	XML_Parser parser;
	struct xml_data data;

	parser = XML_ParserCreate(NULL);
	if(!parser) {
		if(verb) printf("could not XML_ParserCreate\n");
		exit(0);
	}

	/* setup callbacks */
	xml_parse_setup(parser, &data, now);

	/* parse it */
	(void)BIO_seek(xml, 0);
	len = (int)BIO_get_mem_data(xml, &pp);
	if(!len || !pp) {
		if(verb) printf("out of memory\n");
		exit(0);
	}
	if(!XML_Parse(parser, pp, len, 1 /*isfinal*/ )) {
		const char *e = XML_ErrorString(XML_GetErrorCode(parser));
		if(verb) printf("XML_Parse failure %s\n", e?e:"");
		exit(0);
	}

	/* parsed */
	if(verb) printf("XML was parsed successfully, %d keys\n",
			data.num_keys);
	free(data.tag);
	XML_ParserFree(parser);

	if(verb >= 4) {
		(void)BIO_seek(data.ds, 0);
		len = BIO_get_mem_data(data.ds, &pp);
		printf("got DS bio %d: '", len);
		if(!fwrite(pp, (size_t)len, 1, stdout))
			/* compilers do not allow us to ignore fwrite .. */
			fprintf(stderr, "error writing to stdout\n");
		printf("'\n");
	}
	BIO_free(data.czone);
	BIO_free(data.ctag);
	BIO_free(data.calgo);
	BIO_free(data.cdigtype);
	BIO_free(data.cdigest);

	if(data.num_keys == 0) {
		/* the root zone seems to have gone insecure */
		BIO_free(data.ds);
		return NULL;
	} else {
		return data.ds;
	}
}