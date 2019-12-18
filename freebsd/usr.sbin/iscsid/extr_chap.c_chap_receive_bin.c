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
struct chap {int /*<<< orphan*/  chap_response; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_debugx (char*,size_t,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static int
chap_receive_bin(struct chap *chap, void *response, size_t response_len)
{

	if (response_len != sizeof(chap->chap_response)) {
		log_debugx("got CHAP response with invalid length; "
		    "got %zd, should be %zd",
		    response_len, sizeof(chap->chap_response));
		return (1);
	}

	memcpy(chap->chap_response, response, response_len);
	return (0);
}