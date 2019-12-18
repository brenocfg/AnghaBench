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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stderr, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
"usage: fetch [-146AadFlMmnPpqRrsUv] [-B bytes] [--bind-address=host]",
"       [--ca-cert=file] [--ca-path=dir] [--cert=file] [--crl=file]",
"       [-i file] [--key=file] [-N file] [--no-passive] [--no-proxy=list]",
"       [--no-sslv3] [--no-tlsv1] [--no-verify-hostname] [--no-verify-peer]",
"       [-o file] [--referer=URL] [-S bytes] [-T seconds]",
"       [--user-agent=agent-string] [-w seconds] URL ...",
"       fetch [-146AadFlMmnPpqRrsUv] [-B bytes] [--bind-address=host]",
"       [--ca-cert=file] [--ca-path=dir] [--cert=file] [--crl=file]",
"       [-i file] [--key=file] [-N file] [--no-passive] [--no-proxy=list]",
"       [--no-sslv3] [--no-tlsv1] [--no-verify-hostname] [--no-verify-peer]",
"       [-o file] [--referer=URL] [-S bytes] [-T seconds]",
"       [--user-agent=agent-string] [-w seconds] -h host -f file [-c dir]");
}