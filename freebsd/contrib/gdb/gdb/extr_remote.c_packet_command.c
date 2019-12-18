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
struct remote_state {int /*<<< orphan*/  remote_packet_size; } ;

/* Variables and functions */
 char* alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  getpkt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_packet (char*) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 int /*<<< orphan*/  puts_filtered (char*) ; 
 int /*<<< orphan*/  remote_desc ; 

__attribute__((used)) static void
packet_command (char *args, int from_tty)
{
  struct remote_state *rs = get_remote_state ();
  char *buf = alloca (rs->remote_packet_size);

  if (!remote_desc)
    error ("command can only be used with remote target");

  if (!args)
    error ("remote-packet command requires packet text as argument");

  puts_filtered ("sending: ");
  print_packet (args);
  puts_filtered ("\n");
  putpkt (args);

  getpkt (buf, (rs->remote_packet_size), 0);
  puts_filtered ("received: ");
  print_packet (buf);
  puts_filtered ("\n");
}