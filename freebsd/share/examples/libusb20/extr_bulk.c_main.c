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
typedef  scalar_t__ uint8_t ;
struct libusb20_device {int dummy; } ;
struct libusb20_backend {int dummy; } ;
struct LIBUSB20_DEVICE_DESC_DECODED {int idVendor; int idProduct; } ;

/* Variables and functions */
 size_t BUFLEN ; 
 int EX_USAGE ; 
 unsigned int UINT_MAX ; 
 int /*<<< orphan*/  doit (struct libusb20_device*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 int in_ep ; 
 struct libusb20_backend* libusb20_be_alloc_default () ; 
 struct libusb20_device* libusb20_be_device_foreach (struct libusb20_backend*,struct libusb20_device*) ; 
 int /*<<< orphan*/  libusb20_be_free (struct libusb20_backend*) ; 
 char* libusb20_dev_get_desc (struct libusb20_device*) ; 
 struct LIBUSB20_DEVICE_DESC_DECODED* libusb20_dev_get_device_desc (struct libusb20_device*) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 scalar_t__* out_buf ; 
 scalar_t__ out_ep ; 
 size_t out_len ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 void* strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int strtoul (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
  unsigned int vid = UINT_MAX, pid = UINT_MAX; /* impossible VID:PID */
  int c;

  while ((c = getopt(argc, argv, "i:o:p:v:")) != -1)
    switch (c)
      {
      case 'i':
	in_ep = strtol(optarg, NULL, 0);
	break;

      case 'o':
	out_ep = strtol(optarg, NULL, 0);
	break;

      case 'p':
	pid = strtol(optarg, NULL, 0);
	break;

      case 'v':
	vid = strtol(optarg, NULL, 0);
	break;

      default:
	usage();
	break;
      }
  argc -= optind;
  argv += optind;

  if (vid != UINT_MAX || pid != UINT_MAX)
    {
      if (in_ep == 0 || out_ep == 0)
	{
	  usage();
	}
      if ((in_ep & 0x80) == 0)
	{
	  fprintf(stderr, "IN_EP must have bit 7 set\n");
	  return (EX_USAGE);
	}

      if (argc > 0)
	{
	  for (out_len = 0; argc > 0 && out_len < BUFLEN; out_len++, argc--)
	    {
	      unsigned n = strtoul(argv[out_len], 0, 0);
	      if (n > 255)
		fprintf(stderr,
			"Warning: data #%d 0x%0x > 0xff, truncating\n",
			out_len, n);
	      out_buf[out_len] = (uint8_t)n;
	    }
	  out_len++;
	  if (argc > 0)
	    fprintf(stderr,
		    "Data count exceeds maximum of %d, ignoring %d elements\n",
		    BUFLEN, optind);
	}
    }

  struct libusb20_backend *be;
  struct libusb20_device *dev;

  if ((be = libusb20_be_alloc_default()) == NULL)
    {
      perror("libusb20_be_alloc()");
      return 1;
    }

  dev = NULL;
  while ((dev = libusb20_be_device_foreach(be, dev)) != NULL)
    {
      struct LIBUSB20_DEVICE_DESC_DECODED *ddp =
      libusb20_dev_get_device_desc(dev);

      printf("Found device %s (VID:PID = 0x%04x:0x%04x)\n",
	     libusb20_dev_get_desc(dev),
	     ddp->idVendor, ddp->idProduct);

      if (ddp->idVendor == vid && ddp->idProduct == pid)
	doit(dev);
    }

  libusb20_be_free(be);
  return 0;
}