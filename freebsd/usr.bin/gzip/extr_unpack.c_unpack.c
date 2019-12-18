#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  uncompressed_size; } ;
typedef  TYPE_1__ unpack_descriptor_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int dup (int) ; 
 int /*<<< orphan*/  maybe_err (char*) ; 
 int /*<<< orphan*/  unpack_decode (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unpack_descriptor_fini (TYPE_1__*) ; 
 int /*<<< orphan*/  unpack_parse_header (int,int,char*,size_t,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static off_t
unpack(int in, int out, char *pre, size_t prelen, off_t *bytes_in)
{
	unpack_descriptor_t unpackd;

	in = dup(in);
	if (in == -1)
		maybe_err("dup");
	out = dup(out);
	if (out == -1)
		maybe_err("dup");

	unpack_parse_header(in, out, pre, prelen, bytes_in, &unpackd);
	unpack_decode(&unpackd, bytes_in);
	unpack_descriptor_fini(&unpackd);

	/* If we reached here, the unpack was successful */
	return (unpackd.uncompressed_size);
}