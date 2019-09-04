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
struct sockaddr_in {scalar_t__ sin_family; scalar_t__ sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ntohs (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*,int) ; 
 scalar_t__ uv_ip4_addr (char const*,int,struct sockaddr_in*) ; 
 int uv_ip4_name (struct sockaddr_in*,char*,int) ; 

__attribute__((used)) static void check_sockname(struct sockaddr* addr, const char* compare_ip,
  int compare_port, const char* context) {
  struct sockaddr_in check_addr = *(struct sockaddr_in*) addr;
  struct sockaddr_in compare_addr;
  char check_ip[17];
  int r;

  ASSERT(0 == uv_ip4_addr(compare_ip, compare_port, &compare_addr));

  /* Both addresses should be ipv4 */
  ASSERT(check_addr.sin_family == AF_INET);
  ASSERT(compare_addr.sin_family == AF_INET);

  /* Check if the ip matches */
  ASSERT(memcmp(&check_addr.sin_addr,
         &compare_addr.sin_addr,
         sizeof compare_addr.sin_addr) == 0);

  /* Check if the port matches. If port == 0 anything goes. */
  ASSERT(compare_port == 0 || check_addr.sin_port == compare_addr.sin_port);

  r = uv_ip4_name(&check_addr, (char*) check_ip, sizeof check_ip);
  ASSERT(r == 0);

  printf("%s: %s:%d\n", context, check_ip, ntohs(check_addr.sin_port));
}