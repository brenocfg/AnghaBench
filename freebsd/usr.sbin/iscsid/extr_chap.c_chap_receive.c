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
struct chap {int dummy; } ;

/* Variables and functions */
 int chap_hex2bin (char const*,void**,size_t*) ; 
 int chap_receive_bin (struct chap*,void*,size_t) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  log_debugx (char*,char const*) ; 

int
chap_receive(struct chap *chap, const char *response)
{
	void *response_bin;
	size_t response_bin_len;
	int error;

	error = chap_hex2bin(response, &response_bin, &response_bin_len);
	if (error != 0) {
		log_debugx("got incorrectly encoded CHAP response \"%s\"",
		    response);
		return (1);
	}

	error = chap_receive_bin(chap, response_bin, response_bin_len);
	free(response_bin);

	return (error);
}