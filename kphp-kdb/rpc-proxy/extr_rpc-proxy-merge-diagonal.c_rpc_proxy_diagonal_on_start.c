void *rpc_proxy_diagonal_on_start (void) {
  int *extra = malloc (3 * sizeof (int));
  extra[0] = 0;
  extra[1] = 0;
  extra[2] = 0;
  return extra;
}