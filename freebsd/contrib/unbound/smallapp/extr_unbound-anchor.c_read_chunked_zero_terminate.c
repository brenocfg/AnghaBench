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
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_get_mem_data (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/ * do_chunked_read (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int verb ; 

__attribute__((used)) static char*
read_chunked_zero_terminate(SSL* ssl, size_t* len)
{
	/* do the chunked version */
	BIO* tmp = do_chunked_read(ssl);
	char* data, *d = NULL;
	size_t l;
	if(!tmp) {
		if(verb) printf("could not read from https\n");
		return NULL;
	}
	l = (size_t)BIO_get_mem_data(tmp, &d);
	if(verb>=2) printf("chunked data is %d\n", (int)l);
	if(l == 0 || d == NULL) {
		if(verb) printf("out of memory\n");
		return NULL;
	}
	*len = l-1;
	data = (char*)malloc(l);
	if(data == NULL) {
		if(verb) printf("out of memory\n");
		return NULL;
	}
	memcpy(data, d, l);
	BIO_free(tmp);
	return data;
}