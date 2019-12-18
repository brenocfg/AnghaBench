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

/* Variables and functions */
 scalar_t__ SSL_ERROR_ZERO_RETURN ; 
 scalar_t__ SSL_get_error (int /*<<< orphan*/ *,int) ; 
 int SSL_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int verb ; 

__attribute__((used)) static char*
read_data_chunk(SSL* ssl, size_t len)
{
	size_t got = 0;
	int r;
	char* data;
	if(len >= 0xfffffff0)
		return NULL; /* to protect against integer overflow in malloc*/
	data = malloc(len+1);
	if(!data) {
		if(verb) printf("out of memory\n");
		return NULL;
	}
	while(got < len) {
		if((r = SSL_read(ssl, data+got, (int)(len-got))) <= 0) {
			if(SSL_get_error(ssl, r) == SSL_ERROR_ZERO_RETURN) {
				/* EOF */
				if(verb) printf("could not SSL_read: unexpected EOF\n");
				free(data);
				return NULL;
			}
			if(verb) printf("could not SSL_read\n");
			free(data);
			return NULL;
		}
		if(verb >= 2) printf("at %d/%d\n", (int)got, (int)len);
		got += r;
	}
	if(verb>=2) printf("read %d data\n", (int)len);
	data[len] = 0;
	return data;
}