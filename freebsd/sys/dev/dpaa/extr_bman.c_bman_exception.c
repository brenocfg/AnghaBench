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
typedef  struct bman_softc* t_Handle ;
struct bman_softc {int /*<<< orphan*/  sc_dev; } ;
typedef  int e_BmExceptions ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char const*) ; 
#define  e_BM_EX_FBPR_THRESHOLD 131 
#define  e_BM_EX_INVALID_COMMAND 130 
#define  e_BM_EX_MULTI_ECC 129 
#define  e_BM_EX_SINGLE_ECC 128 

__attribute__((used)) static void
bman_exception(t_Handle h_App, e_BmExceptions exception)
{
	struct bman_softc *sc;
	const char *message;

	sc = h_App;

	switch (exception) {
    	case e_BM_EX_INVALID_COMMAND:
		message = "Invalid Command Verb";
		break;
	case e_BM_EX_FBPR_THRESHOLD:
		message = "FBPR pool exhaused. Consider increasing "
		    "BMAN_MAX_BUFFERS";
		break;
	case e_BM_EX_SINGLE_ECC:
		message = "Single bit ECC error";
		break;
	case e_BM_EX_MULTI_ECC:
		message = "Multi bit ECC error";
		break;
	default:
		message = "Unknown error";
	}

	device_printf(sc->sc_dev, "BMAN Exception: %s.\n", message);
}