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
 char* FullVersionStr ; 
 int MAX_CONNECTIONS ; 
 int TCP_PORT ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int) ; 
 int threads_limit ; 

void usage (void) {
  printf ("usage: image-engine [-d] [-v] [-p<port>] [-u<username>] [-g<groupname>] [-c<max-conn>] [-l<log_name>] [-P<max-child-process-number>][-H<max-all-child-process-result>] [-n<nice>] [-N<nice>] [-A<area>] [-M<memory>]\n"
          "%s\n"
          "[-p<port>]\tTCP port number to listen on (default: %d)\n"
          "[-u<username>]\tassume identity of <username> (only when run as root)\n"
          "[-c<max_conn>]\tmax simultaneous connections, default is %d\n"
          "[-v]\t\tverbose\n"
          "[-h]\t\tprint this help and exit\n"
          "[-b<backlog>]\n"
          "[-l<log_name>]\tlog... about something\n"
          "[-P<max-child-process-number>]\t\n"
          "[-H<max-all-child-process-result>]\tdefault 16m\n"
          "[-n<nice>]\tset main process nice (range from -20 to 19)\n"
          "[-N<nice>]\tset job process nice (range from -20 to 19)\n"
          "[-M<memory>]\tset GraphicsMagick memory limit (default: 256m)\n"
          "[-R<memory>]\tset resident set size limit (default: 1g)\n"
          "[-A<area>]\tset max load image area in pixels\n"
          "[-T<threads>]\tset threads limit (default: %d)\n",
          FullVersionStr,
          TCP_PORT,
          MAX_CONNECTIONS,
          threads_limit
         );
  exit (2);
}