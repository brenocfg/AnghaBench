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
struct packet_reg {int /*<<< orphan*/  regnum; int /*<<< orphan*/  pnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_REGISTER_RAW_SIZE (int /*<<< orphan*/ ) ; 
 int MAX_REGISTER_SIZE ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bin2hex (char*,char*,int /*<<< orphan*/ ) ; 
 struct remote_state* get_remote_state () ; 
 struct packet_reg* packet_reg_from_regnum (struct remote_state*,int) ; 
 char* phex_nz (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_collect (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  remote_send (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
store_register_using_P (int regnum)
{
  struct remote_state *rs = get_remote_state ();
  struct packet_reg *reg = packet_reg_from_regnum (rs, regnum);
  /* Try storing a single register.  */
  char *buf = alloca (rs->remote_packet_size);
  char regp[MAX_REGISTER_SIZE];
  char *p;
  int i;

  sprintf (buf, "P%s=", phex_nz (reg->pnum, 0));
  p = buf + strlen (buf);
  regcache_collect (reg->regnum, regp);
  bin2hex (regp, p, DEPRECATED_REGISTER_RAW_SIZE (reg->regnum));
  remote_send (buf, rs->remote_packet_size);

  return buf[0] != '\0';
}