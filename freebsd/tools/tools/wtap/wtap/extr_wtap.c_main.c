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
 int /*<<< orphan*/  O_RDONLY ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  create (int) ; 
 int /*<<< orphan*/  delete (int) ; 
 scalar_t__ dev ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main( int argc, const char* argv[])
{
    if(argc != 3){
      printf("usage: %s [c | d] wtap_id\n", argv[0]);
      return -1;
    }
    int id = atoi(argv[2]);
    if(!(id >= 0 && id < 64)){
	printf("wtap_id must be between 0 and 7\n");
	return -1;
    }
    dev = open("/dev/wtapctl", O_RDONLY);
    if(dev < 0){
      printf("error opening wtapctl cdev\n");
      return -1;
    }
    switch((char)*argv[1]){
      case 'c':
	create(id);
	break;
      case 'd':
	delete(id);
	break;
      default:
	printf("wtap ioctl: unknown command '%c'\n", *argv[1]);
	return -1;
    }
    return 0;
}