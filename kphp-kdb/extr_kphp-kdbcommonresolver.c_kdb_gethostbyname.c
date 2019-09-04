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
struct hostent {char* h_name; } ;
struct host {int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  Hosts ; 
 struct host* getHash (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gethostbyname (char const*) ; 
 struct hostent* gethostbyname2 (char const*,int /*<<< orphan*/ ) ; 
 struct hostent hret ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipaddr ; 
 scalar_t__ kdb_hosts_loaded ; 
 int /*<<< orphan*/  kdb_load_hosts () ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ strchr (char const*,char) ; 
 int strlen (char const*) ; 

struct hostent *kdb_gethostbyname (const char *name) {
  if (!kdb_hosts_loaded) {
    kdb_load_hosts ();
  }

  int len = strlen (name);


  if (name[0] == '[' && name[len-1] == ']' && len <= 64) {
    /*
    if (parse_ipv6 ((unsigned short *) ipv6_addr, name + 1) == len - 2) {
      hret6.h_name = (char *)name;
      return &hret6;
    }
    */
    char buf[64];
    memcpy (buf, name + 1, len - 2);
    buf[len - 2] = 0;
    return gethostbyname2 (buf, AF_INET6);
  }


  if (kdb_hosts_loaded <= 0) {
    return gethostbyname (name) ?: gethostbyname2 (name, AF_INET6);
  }

  if (len >= 128) {
    return gethostbyname (name) ?: gethostbyname2 (name, AF_INET6);
  }

  struct host *res = getHash (&Hosts, name, len, 0);

  if (!res) {
    if (strchr (name, '.') || strchr (name, ':')) {
      return gethostbyname (name) ?: gethostbyname2 (name, AF_INET6);
    } else {
      return 0;
    }
  }

  hret.h_name = (char *)name;
  ipaddr = htonl (res->ip);
  return &hret;
}