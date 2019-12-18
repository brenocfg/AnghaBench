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
typedef  int usb_size_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct usb_mbuf {int cur_data_len; int max_data_len; int /*<<< orphan*/ * min_data_ptr; int /*<<< orphan*/ * cur_data_ptr; } ;
struct usb_ifqueue {int dummy; } ;
struct malloc_type {int dummy; } ;

/* Variables and functions */
 int M_WAITOK ; 
 int M_ZERO ; 
 int USB_HOST_ALIGN ; 
 int /*<<< orphan*/  USB_IF_ENQUEUE (struct usb_ifqueue*,struct usb_mbuf*) ; 
 void* malloc (int,struct malloc_type*,int) ; 

void   *
usb_alloc_mbufs(struct malloc_type *type, struct usb_ifqueue *ifq,
    usb_size_t block_size, uint16_t nblocks)
{
	struct usb_mbuf *m_ptr;
	uint8_t *data_ptr;
	void *free_ptr = NULL;
	usb_size_t alloc_size;

	/* align data */
	block_size += ((-block_size) & (USB_HOST_ALIGN - 1));

	if (nblocks && block_size) {

		alloc_size = (block_size + sizeof(struct usb_mbuf)) * nblocks;

		free_ptr = malloc(alloc_size, type, M_WAITOK | M_ZERO);

		if (free_ptr == NULL) {
			goto done;
		}
		m_ptr = free_ptr;
		data_ptr = (void *)(m_ptr + nblocks);

		while (nblocks--) {

			m_ptr->cur_data_ptr =
			    m_ptr->min_data_ptr = data_ptr;

			m_ptr->cur_data_len =
			    m_ptr->max_data_len = block_size;

			USB_IF_ENQUEUE(ifq, m_ptr);

			m_ptr++;
			data_ptr += block_size;
		}
	}
done:
	return (free_ptr);
}