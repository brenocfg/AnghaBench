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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 scalar_t__ BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  parse_chunk_header (char*,size_t*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* read_data_chunk (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ read_ssl_line (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ strlen (char*) ; 
 int verb ; 

__attribute__((used)) static BIO*
do_chunked_read(SSL* ssl)
{
	char buf[1024];
	size_t len;
	char* body;
	BIO* mem = BIO_new(BIO_s_mem());
	if(verb>=3) printf("do_chunked_read\n");
	if(!mem) {
		if(verb) printf("out of memory\n");
		return NULL;
	}
	while(read_ssl_line(ssl, buf, sizeof(buf))) {
		/* read the chunked start line */
		if(verb>=2) printf("chunk header: %s\n", buf);
		if(!parse_chunk_header(buf, &len)) {
			BIO_free(mem);
			if(verb>=3) printf("could not parse chunk header\n");
			return NULL;
		}
		if(verb>=2) printf("chunk len: %d\n", (int)len);
		/* are we done? */
		if(len == 0) {
			char z = 0;
			/* skip end-of-chunk-trailer lines,
			 * until the empty line after that */
			do {
				if(!read_ssl_line(ssl, buf, sizeof(buf))) {
					BIO_free(mem);
					return NULL;
				}
			} while (strlen(buf) > 0);
			/* end of chunks, zero terminate it */
			if(BIO_write(mem, &z, 1) <= 0) {
				if(verb) printf("out of memory\n");
				BIO_free(mem);
				return NULL;
			}
			return mem;
		}
		/* read the chunked body */
		body = read_data_chunk(ssl, len);
		if(!body) {
			BIO_free(mem);
			return NULL;
		}
		if(BIO_write(mem, body, (int)len) <= 0) {
			if(verb) printf("out of memory\n");
			free(body);
			BIO_free(mem);
			return NULL;
		}
		free(body);
		/* skip empty line after data chunk */
		if(!read_ssl_line(ssl, buf, sizeof(buf))) {
			BIO_free(mem);
			return NULL;
		}
	}
	BIO_free(mem);
	return NULL;
}