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
struct strbuf {int dummy; } ;
typedef  enum sideband_type { ____Placeholder_sideband_type } sideband_type ;

/* Variables and functions */
 int /*<<< orphan*/  LARGE_PACKET_MAX ; 
#define  SIDEBAND_PRIMARY 128 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  demultiplex_sideband (char const*,char*,int,int /*<<< orphan*/ ,struct strbuf*,int*) ; 
 int packet_read (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_or_die (int,char*,int) ; 

int recv_sideband(const char *me, int in_stream, int out)
{
	char buf[LARGE_PACKET_MAX + 1];
	int len;
	struct strbuf scratch = STRBUF_INIT;
	enum sideband_type sideband_type;

	while (1) {
		len = packet_read(in_stream, NULL, NULL, buf, LARGE_PACKET_MAX,
				  0);
		if (!demultiplex_sideband(me, buf, len, 0, &scratch,
					  &sideband_type))
			continue;
		switch (sideband_type) {
		case SIDEBAND_PRIMARY:
			write_or_die(out, buf + 1, len - 1);
			break;
		default: /* errors: message already written */
			return sideband_type;
		}
	}
}