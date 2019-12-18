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
struct device {int /*<<< orphan*/  queue; int /*<<< orphan*/  release_rx_buf; int /*<<< orphan*/  peek_rx_buf; int /*<<< orphan*/  get_rx_buf; int /*<<< orphan*/ * copy_rx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  RECEIVE_BUF_SIZE ; 
 int /*<<< orphan*/  RECEIVE_QUEUE_SIZE ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  exc_handler ; 
 int /*<<< orphan*/  get_rxbuf ; 
 int /*<<< orphan*/  init_32bit () ; 
 int /*<<< orphan*/ * k_calloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  k_free (int /*<<< orphan*/ *) ; 
 struct device* open_driver (char const*,char*,int) ; 
 int /*<<< orphan*/  peek_rxbuf ; 
 int /*<<< orphan*/  pktq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_rxbuf ; 
 int /*<<< orphan*/ * rx_pool ; 
 int /*<<< orphan*/  setup_signals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int first_init (const char *name, char *ebuf, int promisc)
{
  struct device *dev;

#ifdef USE_32BIT_DRIVERS
  rx_pool = k_calloc (RECEIVE_BUF_SIZE, RECEIVE_QUEUE_SIZE);
  if (!rx_pool)
  {
    strcpy (ebuf, "Not enough memory (Rx pool)");
    return (0);
  }
#endif

#ifdef __DJGPP__
  setup_signals (exc_handler);
#endif

#ifdef USE_32BIT_DRIVERS
  init_32bit();
#endif

  dev = open_driver (name, ebuf, promisc);
  if (!dev)
  {
#ifdef USE_32BIT_DRIVERS
    k_free (rx_pool);
    rx_pool = NULL;
#endif

#ifdef __DJGPP__
    setup_signals (SIG_DFL);
#endif
    return (0);
  }

#ifdef USE_32BIT_DRIVERS
  /*
   * If driver is NOT a 16-bit "pkt/ndis" driver (having a 'copy_rx_buf'
   * set in it's probe handler), initialise near-memory ring-buffer for
   * the 32-bit device.
   */
  if (dev->copy_rx_buf == NULL)
  {
    dev->get_rx_buf     = get_rxbuf;
    dev->peek_rx_buf    = peek_rxbuf;
    dev->release_rx_buf = release_rxbuf;
    pktq_init (&dev->queue, RECEIVE_BUF_SIZE, RECEIVE_QUEUE_SIZE, rx_pool);
  }
#endif
  return (1);
}