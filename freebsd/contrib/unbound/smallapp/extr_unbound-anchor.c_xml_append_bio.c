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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 long BIO_get_mem_data (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  BIO_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_write (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ verb ; 

__attribute__((used)) static void
xml_append_bio(BIO* b, BIO* a)
{
	char* z = NULL;
	long i, len;
	(void)BIO_seek(a, 0);
	len = BIO_get_mem_data(a, &z);
	if(!len || !z) {
		if(verb) printf("out of memory in BIO_write\n");
		exit(0);
	}
	/* remove newlines in the data here */
	for(i=0; i<len; i++) {
		if(z[i] == '\r' || z[i] == '\n')
			z[i] = ' ';
	}
	/* write to BIO */
	if(BIO_write(b, z, len) < 0) {
		if(verb) printf("out of memory in BIO_write\n");
		exit(0);
	}
}