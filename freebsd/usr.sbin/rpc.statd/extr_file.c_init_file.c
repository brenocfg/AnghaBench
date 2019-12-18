#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {int noOfHosts; int ourState; TYPE_1__* hosts; } ;
struct TYPE_4__ {int /*<<< orphan*/ * monList; void* notifyReqd; } ;
typedef  TYPE_1__ HostInfo ;
typedef  TYPE_2__ FileLayout ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int FALSE ; 
 int HEADER_LEN ; 
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 void* TRUE ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 scalar_t__ lseek (scalar_t__,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ open (char const*,int,...) ; 
 scalar_t__ status_fd ; 
 scalar_t__ status_file_len ; 
 TYPE_2__* status_info ; 
 int /*<<< orphan*/  warnx (char*) ; 
 int /*<<< orphan*/  write (scalar_t__,char*,int) ; 

void init_file(const char *filename)
{
  int new_file = FALSE;
  char buf[HEADER_LEN];
  int i;

  /* try to open existing file - if not present, create one		*/
  status_fd = open(filename, O_RDWR);
  if ((status_fd < 0) && (errno == ENOENT))
  {
    status_fd = open(filename, O_RDWR | O_CREAT, 0644);
    new_file = TRUE;
  }
  if (status_fd < 0)
    errx(1, "unable to open status file %s", filename);

  /* File now open.  mmap() it, with a generous size to allow for	*/
  /* later growth, where we will extend the file but not re-map it.	*/
  status_info = (FileLayout *)
    mmap(NULL, 0x10000000, PROT_READ | PROT_WRITE, MAP_SHARED, status_fd, 0);

  if (status_info == (FileLayout *) MAP_FAILED)
    err(1, "unable to mmap() status file");

  status_file_len = lseek(status_fd, 0L, SEEK_END);

  /* If the file was not newly created, validate the contents, and if	*/
  /* defective, re-create from scratch.					*/
  if (!new_file)
  {
    if ((status_file_len < (off_t)HEADER_LEN) || (status_file_len
      < (off_t)(HEADER_LEN + sizeof(HostInfo) * status_info->noOfHosts)) )
    {
      warnx("status file is corrupt");
      new_file = TRUE;
    }
  }

  /* Initialisation of a new, empty file.				*/
  if (new_file)
  {
    memset(buf, 0, sizeof(buf));
    lseek(status_fd, 0L, SEEK_SET);
    write(status_fd, buf, HEADER_LEN);
    status_file_len = HEADER_LEN;
  }
  else
  {
    /* Clean-up of existing file - monitored hosts will have a pointer	*/
    /* to a list of clients, which refers to memory in the previous	*/
    /* incarnation of the program and so are meaningless now.  These	*/
    /* pointers are zeroed and the fact that the host was previously	*/
    /* monitored is recorded by setting the notifyReqd flag, which will	*/
    /* in due course cause a SM_NOTIFY to be sent.			*/
    /* Note that if we crash twice in quick succession, some hosts may	*/
    /* already have notifyReqd set, where we didn't manage to notify	*/
    /* them before the second crash occurred.				*/
    for (i = 0; i < status_info->noOfHosts; i++)
    {
      HostInfo *this_host = &status_info->hosts[i];

      if (this_host->monList)
      {
	this_host->notifyReqd = TRUE;
	this_host->monList = NULL;
      }
    }
    /* Select the next higher even number for the state counter		*/
    status_info->ourState = (status_info->ourState + 2) & 0xfffffffe;
/*???????******/ status_info->ourState++;
  }
}