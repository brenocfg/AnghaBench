#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ auth_context; int /*<<< orphan*/  auth_challenges; scalar_t__ authenticated; } ;
typedef  TYPE_1__ http_server ;

/* Variables and functions */
 scalar_t__ auth_context_complete (TYPE_1__*) ; 
 int /*<<< orphan*/  free_auth_context (TYPE_1__*) ; 
 scalar_t__ git_vector_length (int /*<<< orphan*/ *) ; 
 int set_authentication_challenge (TYPE_1__*) ; 
 int set_authentication_types (TYPE_1__*) ; 

__attribute__((used)) static int parse_authenticate_response(http_server *server)
{
	/*
	 * If we think that we've completed authentication (ie, we've either
	 * sent a basic credential or we've sent the NTLM/Negotiate response)
	 * but we've got an authentication request from the server then our
	 * last authentication did not succeed.  Start over.
	 */
	if (server->auth_context && auth_context_complete(server)) {
		free_auth_context(server);

		server->authenticated = 0;
	}

	/*
	 * If we've begun authentication, give the challenge to the context.
	 * Otherwise, set up the types to prepare credentials.
	 */
	if (git_vector_length(&server->auth_challenges) == 0)
		return 0;
	else if (server->auth_context)
		return set_authentication_challenge(server);
	else
		return set_authentication_types(server);
}