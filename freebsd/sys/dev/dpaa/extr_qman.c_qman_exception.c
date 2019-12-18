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
typedef  struct qman_softc* t_Handle ;
struct qman_softc {int /*<<< orphan*/  sc_dev; } ;
typedef  int e_QmExceptions ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char const*) ; 
#define  e_QM_EX_CG_STATE_CHANGE 144 
#define  e_QM_EX_CORENET_INITIATOR_DATA 143 
#define  e_QM_EX_CORENET_INVALID_TARGET_TRANSACTION 142 
#define  e_QM_EX_CORENET_TARGET_DATA 141 
#define  e_QM_EX_DEQUEUE_DCP 140 
#define  e_QM_EX_DEQUEUE_FQ 139 
#define  e_QM_EX_DEQUEUE_QUEUE 138 
#define  e_QM_EX_DEQUEUE_SOURCE 137 
#define  e_QM_EX_ENQUEUE_CHANNEL 136 
#define  e_QM_EX_ENQUEUE_OVERFLOW 135 
#define  e_QM_EX_ENQUEUE_QUEUE 134 
#define  e_QM_EX_ENQUEUE_STATE 133 
#define  e_QM_EX_INVALID_COMMAND 132 
#define  e_QM_EX_MULTI_ECC 131 
#define  e_QM_EX_PFDR_ENQUEUE_BLOCKED 130 
#define  e_QM_EX_PFDR_THRESHOLD 129 
#define  e_QM_EX_SINGLE_ECC 128 

__attribute__((used)) static void
qman_exception(t_Handle app, e_QmExceptions exception)
{
	struct qman_softc *sc;
	const char *message;

	sc = app;

	switch (exception) {
	case e_QM_EX_CORENET_INITIATOR_DATA:
		message = "Initiator Data Error";
		break;
	case e_QM_EX_CORENET_TARGET_DATA:
		message = "CoreNet Target Data Error";
		break;
	case e_QM_EX_CORENET_INVALID_TARGET_TRANSACTION:
		message = "Invalid Target Transaction";
		break;
	case e_QM_EX_PFDR_THRESHOLD:
		message = "PFDR Low Watermark Interrupt";
		break;
	case e_QM_EX_PFDR_ENQUEUE_BLOCKED:
		message = "PFDR Enqueues Blocked Interrupt";
		break;
	case e_QM_EX_SINGLE_ECC:
		message = "Single Bit ECC Error Interrupt";
		break;
	case e_QM_EX_MULTI_ECC:
		message = "Multi Bit ECC Error Interrupt";
		break;
	case e_QM_EX_INVALID_COMMAND:
		message = "Invalid Command Verb Interrupt";
		break;
	case e_QM_EX_DEQUEUE_DCP:
		message = "Invalid Dequeue Direct Connect Portal Interrupt";
		break;
	case e_QM_EX_DEQUEUE_FQ:
		message = "Invalid Dequeue FQ Interrupt";
		break;
	case e_QM_EX_DEQUEUE_SOURCE:
		message = "Invalid Dequeue Source Interrupt";
		break;
	case e_QM_EX_DEQUEUE_QUEUE:
		message = "Invalid Dequeue Queue Interrupt";
		break;
	case e_QM_EX_ENQUEUE_OVERFLOW:
		message = "Invalid Enqueue Overflow Interrupt";
		break;
	case e_QM_EX_ENQUEUE_STATE:
		message = "Invalid Enqueue State Interrupt";
		break;
	case e_QM_EX_ENQUEUE_CHANNEL:
		message = "Invalid Enqueue Channel Interrupt";
		break;
	case e_QM_EX_ENQUEUE_QUEUE:
		message = "Invalid Enqueue Queue Interrupt";
		break;
	case e_QM_EX_CG_STATE_CHANGE:
		message = "CG change state notification";
		break;
	default:
		message = "Unknown error";
	}

	device_printf(sc->sc_dev, "QMan Exception: %s.\n", message);
}