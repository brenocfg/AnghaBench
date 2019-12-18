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
struct signature_check {char* gpg_status; char* gpg_output; char const* payload; } ;

/* Variables and functions */
 unsigned int GPG_VERIFY_RAW ; 
 unsigned int GPG_VERIFY_VERBOSE ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

void print_signature_buffer(const struct signature_check *sigc, unsigned flags)
{
	const char *output = flags & GPG_VERIFY_RAW ?
		sigc->gpg_status : sigc->gpg_output;

	if (flags & GPG_VERIFY_VERBOSE && sigc->payload)
		fputs(sigc->payload, stdout);

	if (output)
		fputs(output, stderr);
}