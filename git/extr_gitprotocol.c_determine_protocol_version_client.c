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
typedef  enum protocol_version { ____Placeholder_protocol_version } protocol_version ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 int parse_protocol_version (char const*) ; 
 int protocol_unknown_version ; 
 int protocol_v0 ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 

enum protocol_version determine_protocol_version_client(const char *server_response)
{
	enum protocol_version version = protocol_v0;

	if (skip_prefix(server_response, "version ", &server_response)) {
		version = parse_protocol_version(server_response);

		if (version == protocol_unknown_version)
			die("server is speaking an unknown protocol");
		if (version == protocol_v0)
			die("protocol error: server explicitly said version 0");
	}

	return version;
}