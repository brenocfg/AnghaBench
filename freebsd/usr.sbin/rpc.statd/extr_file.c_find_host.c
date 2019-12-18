#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct addrinfo {scalar_t__ ai_family; scalar_t__ ai_addrlen; int /*<<< orphan*/  ai_addr; struct addrinfo* ai_next; } ;
typedef  int off_t ;
struct TYPE_6__ {int noOfHosts; TYPE_1__* hosts; } ;
struct TYPE_5__ {char* hostname; int /*<<< orphan*/  notifyReqd; int /*<<< orphan*/  monList; } ;
typedef  TYPE_1__ HostInfo ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SM_MAXSTRLEN ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 scalar_t__ getaddrinfo (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct addrinfo**) ; 
 int lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  status_fd ; 
 int status_file_len ; 
 TYPE_2__* status_info ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ write (int /*<<< orphan*/ ,char*,int) ; 

HostInfo *find_host(char *hostname, int create)
{
  HostInfo *hp;
  HostInfo *spare_slot = NULL;
  HostInfo *result = NULL;
  struct addrinfo *ai1, *ai2;
  int i;

  ai2 = NULL;
  if (getaddrinfo(hostname, NULL, NULL, &ai1) != 0)
    ai1 = NULL;
  for (i = 0, hp = status_info->hosts; i < status_info->noOfHosts; i++, hp++)
  {
    if (!strncasecmp(hostname, hp->hostname, SM_MAXSTRLEN))
    {
      result = hp;
      break;
    }
    if (hp->hostname[0] != '\0' &&
	getaddrinfo(hp->hostname, NULL, NULL, &ai2) != 0)
      ai2 = NULL;
    if (ai1 && ai2)
    {
       struct addrinfo *p1, *p2;
       for (p1 = ai1; !result && p1; p1 = p1->ai_next)
       {
	 for (p2 = ai2; !result && p2; p2 = p2->ai_next)
	 {
	   if (p1->ai_family == p2->ai_family
	       && p1->ai_addrlen == p2->ai_addrlen
	       && !memcmp(p1->ai_addr, p2->ai_addr, p1->ai_addrlen))
	   {
	     result = hp;
	     break;
	   }
	 }
       }
       if (result)
	 break;
    }
    if (ai2) {
      freeaddrinfo(ai2);
      ai2 = NULL;
    }
    if (!spare_slot && !hp->monList && !hp->notifyReqd)
      spare_slot = hp;
  }
  if (ai1)
    freeaddrinfo(ai1);

  /* Return if entry found, or if not asked to create one.		*/
  if (result || !create) return (result);

  /* Now create an entry, using the spare slot if one was found or	*/
  /* adding to the end of the list otherwise, extending file if reqd	*/
  if (!spare_slot)
  {
    off_t desired_size;
    spare_slot = &status_info->hosts[status_info->noOfHosts];
    desired_size = ((char*)spare_slot - (char*)status_info) + sizeof(HostInfo);
    if (desired_size > status_file_len)
    {
      /* Extend file by writing 1 byte of junk at the desired end pos	*/
      if (lseek(status_fd, desired_size - 1, SEEK_SET) == -1 ||
          write(status_fd, "\0", 1) < 0)
      {
	syslog(LOG_ERR, "Unable to extend status file");
	return (NULL);
      }
      status_file_len = desired_size;
    }
    status_info->noOfHosts++;
  }

  /* Initialise the spare slot that has been found/created		*/
  /* Note that we do not msync(), since the caller is presumed to be	*/
  /* about to modify the entry further					*/
  memset(spare_slot, 0, sizeof(HostInfo));
  strncpy(spare_slot->hostname, hostname, SM_MAXSTRLEN);
  return (spare_slot);
}