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
struct signature_check {int dummy; } ;
typedef  int /*<<< orphan*/  sigc ;

/* Variables and functions */
 unsigned int GPG_VERIFY_OMIT_STATUS ; 
 unsigned int GPG_VERIFY_VERBOSE ; 
 int check_signature (char const*,size_t,char const*,unsigned long,struct signature_check*) ; 
 int error (char*) ; 
 int /*<<< orphan*/  memset (struct signature_check*,int /*<<< orphan*/ ,int) ; 
 size_t parse_signature (char const*,unsigned long) ; 
 int /*<<< orphan*/  print_signature_buffer (struct signature_check*,unsigned int) ; 
 int /*<<< orphan*/  signature_check_clear (struct signature_check*) ; 
 int /*<<< orphan*/  write_in_full (int,char const*,size_t) ; 

__attribute__((used)) static int run_gpg_verify(const char *buf, unsigned long size, unsigned flags)
{
	struct signature_check sigc;
	size_t payload_size;
	int ret;

	memset(&sigc, 0, sizeof(sigc));

	payload_size = parse_signature(buf, size);

	if (size == payload_size) {
		if (flags & GPG_VERIFY_VERBOSE)
			write_in_full(1, buf, payload_size);
		return error("no signature found");
	}

	ret = check_signature(buf, payload_size, buf + payload_size,
				size - payload_size, &sigc);

	if (!(flags & GPG_VERIFY_OMIT_STATUS))
		print_signature_buffer(&sigc, flags);

	signature_check_clear(&sigc);
	return ret;
}