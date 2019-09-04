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
typedef  int /*<<< orphan*/  WSClient ;

/* Variables and functions */
 int read_plain_socket (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
read_socket (WSClient * client, char *buffer, int size)
{
#ifdef HAVE_LIBSSL
  if (wsconfig.use_ssl)
    return read_ssl_socket (client, buffer, size);
  else
    return read_plain_socket (client, buffer, size);
#else
  return read_plain_socket (client, buffer, size);
#endif
}