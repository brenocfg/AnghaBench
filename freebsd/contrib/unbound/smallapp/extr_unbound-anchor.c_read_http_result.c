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
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  print_data (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 char* read_chunked_zero_terminate (int /*<<< orphan*/ *,size_t*) ; 
 char* read_data_chunk (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  read_http_headers (int /*<<< orphan*/ *,size_t*) ; 
 int verb ; 

__attribute__((used)) static BIO*
read_http_result(SSL* ssl)
{
	size_t len = 0;
	char* data;
	BIO* m;
	if(!read_http_headers(ssl, &len)) {
		return NULL;
	}
	if(len == 0) {
		data = read_chunked_zero_terminate(ssl, &len);
	} else {
		data = read_data_chunk(ssl, len);
	}
	if(!data) return NULL;
	if(verb >= 4) print_data("read data", data, (int)len);
	m = BIO_new(BIO_s_mem());
	if(!m) {
		if(verb) printf("out of memory\n");
		free(data);
		exit(0);
	}
	BIO_write(m, data, (int)len);
	free(data);
	return m;
}