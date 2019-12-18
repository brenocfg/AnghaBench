#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct hostent {char* h_name; } ;
typedef  int /*<<< orphan*/  bp_getfile_res ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 struct hostent* gethostbyaddr (char*,int,int /*<<< orphan*/ ) ; 
 char* inet_ntoa (TYPE_1__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printgetfile (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t
eachres_getfile(bp_getfile_res *resultp, struct sockaddr_in *raddr)
{
  struct hostent *he;

  he = gethostbyaddr((char *)&raddr->sin_addr.s_addr,4,AF_INET);
  printf("%s answered:\n", he ? he->h_name : inet_ntoa(raddr->sin_addr));
  printgetfile(resultp);
  printf("\n");
  return(0);
}