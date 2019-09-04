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
 char** I ; 
 char** S ; 
 int /*<<< orphan*/  do_store (char*,char*) ; 
 size_t kad_album ; 
 size_t kad_bitrate ; 
 size_t kad_file ; 
 size_t kad_genre ; 
 size_t kad_print ; 
 size_t kad_uid ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int source_server ; 

void process_kad_row (void) {
  char key_prefix[100], key[200], value[50];
  snprintf (key_prefix, 99, "%d_%lld_%s", source_server, I[kad_uid], S[kad_file]);
  // store kad
  snprintf (key, 199, "%s.kad", key_prefix);
  do_store (key, S[kad_print]);
  // store genre
  snprintf (key, 199, "%s.genre", key_prefix);
  snprintf (value, 49, "%lld", I[kad_genre]);
  do_store (key, value);
  // store bitrate
  snprintf (key, 199, "%s.rate", key_prefix);
  snprintf (value, 49, "%lld", I[kad_bitrate]);
  do_store (key, value);
  // store album
  snprintf (key, 199, "%s.album", key_prefix);
  do_store (key, S[kad_album]);
}